//
// RSADigestEngine.h
//
// $Id: //poco/Main/Crypto/include/Poco/Crypto/RSADigestEngine.h#2 $
//
// Library: Crypto
// Package: RSA
// Module:  RSADigestEngine
//
// Definition of the RSADigestEngine class.
//
// Copyright (c) 2008, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Crypto_RSADigestEngine_INCLUDED
#define Crypto_RSADigestEngine_INCLUDED


#include "Poco/Crypto/Crypto.h"
#include "Poco/Crypto/RSAKey.h"
#include "Poco/DigestEngine.h"
#include "Poco/MD5Engine.h"
#include "Poco/SHA1Engine.h"
#include <openssl/rsa.h>
#include <istream>
#include <ostream>


namespace Poco {
namespace Crypto {


class Crypto_API RSADigestEngine: public Poco::DigestEngine
	/// This class implements a Poco::DigestEngine that can be
	/// used to compute a secure digital signature.
	///
	/// First another Poco::DigestEngine (Poco::MD5Engine
	/// or Poco::SHA1Engine) is used to compute a cryptographic
	/// hash of the data to be signed. Then, the hash value is
	/// encrypted, using the RSA private key.
	///
	/// To verify a signature, pass it to the verify() 
	/// member function. It will decrypt the signature
	/// using the RSA public key and compare the resulting
	/// hash with the actual hash of the data.
{
public:
	enum DigestType
	{
		DIGEST_MD5,
		DIGEST_SHA1
	};
	
	RSADigestEngine(const RSAKey& key, DigestType digestType = DIGEST_SHA1);
		/// Creates the RSADigestEngine with the given RSA key,
		/// using the SHA-1 hash algorithm.

	~RSADigestEngine();
		/// Destroys the RSADigestEngine.

	unsigned digestLength() const;
		/// Returns the length of the digest in bytes.

	void reset();
		/// Resets the engine so that a new
		/// digest can be computed.
		
	const DigestEngine::Digest& digest();
		/// Finishes the computation of the digest 
		/// (the first time it's called) and
		/// returns the message digest. 
		///
		/// Can be called multiple times.

	const DigestEngine::Digest& signature();
		/// Signs the digest using the RSA algorithm
		/// and the private key (teh first time it's
		/// called) and returns the result.
		///
		/// Can be called multiple times.

	bool verify(const DigestEngine::Digest& signature);
		/// Verifies the data against the signature.
		///
		/// Returns true if the signature can be verified, false otherwise.

protected:
	void updateImpl(const void* data, unsigned length);

private:
	RSAKey _key;
	Poco::DigestEngine& _engine;
	int _type;
	Poco::DigestEngine::Digest _digest;
	Poco::DigestEngine::Digest _signature;
	Poco::MD5Engine _md5Engine;
	Poco::SHA1Engine _sha1Engine;
};


} } // namespace Poco::Crypto


#endif // Crypto_RSADigestEngine_INCLUDED
