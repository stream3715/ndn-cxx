/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/**
 * Copyright (c) 2013-2014,  Regents of the University of California.
 * All rights reserved.
 *
 * This file is part of ndn-cxx library (NDN C++ library with eXperimental eXtensions).
 * See AUTHORS.md for complete list of ndn-cxx authors and contributors.
 *
 * This file licensed under New BSD License.  See COPYING for detailed information about
 * ndn-cxx library copyright, permissions, and redistribution restrictions.
 *
 * @author Jeff Thompson <jefft0@remap.ucla.edu>
 */

#ifndef NDN_SECURITY_SEC_PUBLIC_INFO_MEMORY_HPP
#define NDN_SECURITY_SEC_PUBLIC_INFO_MEMORY_HPP

#include "../common.hpp"
#include "sec-public-info.hpp"

#include <map>

namespace ndn {

/**
 * @brief SecPublicInfoMemory extends SecPublicInfo and implements its methods to store identity,
 *        public key and certificate objects in memory.
 */
class SecPublicInfoMemory : public SecPublicInfo
{
public:
  class Error : public SecPublicInfo::Error
  {
  public:
    explicit
    Error(const std::string& what)
      : SecPublicInfo::Error(what)
    {
    }
  };

  virtual
  ~SecPublicInfoMemory();

  virtual bool
  doesIdentityExist(const Name& identityName);

  virtual void
  addIdentity(const Name& identityName);

  virtual bool
  revokeIdentity();

  virtual bool
  doesPublicKeyExist(const Name& keyName);

  virtual void
  addPublicKey(const Name& keyName, KeyType keyType, const PublicKey& publicKeyDer);

  virtual shared_ptr<PublicKey>
  getPublicKey(const Name& keyName);

  virtual bool
  doesCertificateExist(const Name& certificateName);

  virtual void
  addCertificate(const IdentityCertificate& certificate);

  virtual shared_ptr<IdentityCertificate>
  getCertificate(const Name& certificateName);

  virtual Name
  getDefaultIdentity();

  virtual Name
  getDefaultKeyNameForIdentity(const Name& identityName);

  virtual Name
  getDefaultCertificateNameForKey(const Name& keyName);

  virtual void
  getAllIdentities(std::vector<Name>& nameList, bool isDefault);

  virtual void
  getAllKeyNames(std::vector<Name>& nameList, bool isDefault);

  virtual void
  getAllKeyNamesOfIdentity(const Name& identity, std::vector<Name>& nameList, bool isDefault);

  virtual void
  getAllCertificateNames(std::vector<Name>& nameList, bool isDefault);

  virtual void
  getAllCertificateNamesOfKey(const Name& keyName, std::vector<Name>& nameList, bool isDefault);

protected:
  virtual void
  setDefaultIdentityInternal(const Name& identityName);

  virtual void
  setDefaultKeyNameForIdentityInternal(const Name& keyName);

  virtual void
  setDefaultCertificateNameForKeyInternal(const Name& certificateName);

  virtual void
  deleteCertificateInfo(const Name& certificateName);

  virtual void
  deletePublicKeyInfo(const Name& keyName);

  virtual void
  deleteIdentityInfo(const Name& identity);


private:
  class KeyRecord
  {
  public:
    KeyRecord(KeyType keyType, const PublicKey& key)
    : m_keyType(keyType), m_key(key)
    {
    }

    const KeyType
    getKeyType() const
    {
      return m_keyType;
    }

    const PublicKey&
    getKey()
    {
      return m_key;
    }

  private:
    KeyType   m_keyType;
    PublicKey m_key;
  };

  std::vector<std::string> m_identityStore; // A list of name URI.
  std::string m_defaultIdentity; // The default identity in m_identityStore, or "" if not defined.
  Name m_defaultKeyName;
  Name m_defaultCert;

  // The map key is the keyName.toUri()
  typedef std::map<std::string, shared_ptr<KeyRecord> > KeyStore;

  // The map key is the certificateName.toUri()
  typedef std::map<std::string, shared_ptr<IdentityCertificate> > CertificateStore;

  KeyStore m_keyStore;
  CertificateStore m_certificateStore;
};

} // namespace ndn

#endif //NDN_SECURITY_SEC_PUBLIC_INFO_MEMORY_HPP
