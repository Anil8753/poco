//
// CipherFactory.h
//
// $Id$
//
// Library: Crypto
// Package: Cipher
// Module:  CipherFactory
//
// Definition of the CipherFactory class.
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


#ifndef Crypto_CipherFactory_INCLUDED
#define Crypto_CipherFactory_INCLUDED


#include "Poco/Crypto/Crypto.h"


namespace Poco {
namespace Crypto {


class Cipher;
class CipherKey;
class RSAKey;


class Crypto_API CipherFactory
	/// A factory for Cipher objects. See the Cipher class for examples on how to
	/// use the CipherFactory.
{
public:
	CipherFactory();
		/// Creates a new CipherFactory object.

	virtual ~CipherFactory();
		/// Destroys the CipherFactory.

	Cipher* createCipher(const CipherKey& key);
		/// Creates a Cipher object for the given Cipher name. Valid cipher 
		/// names depend on the OpenSSL version the library is linked with;  
		/// see the output of
		///
		///     openssl enc --help
		///
		/// for a list of supported block and stream ciphers.
		///
		/// Common examples are:
		///
		///   * AES: "aes-128", "aes-256"
		///   * DES: "des", "des3"
		///   * Blowfish: "bf"

	Cipher* createCipher(const RSAKey& key, RSAPaddingMode paddingMode = RSA_PADDING_PKCS1);
		/// Creates a RSACipher using the given RSA key and padding mode
		/// for public key encryption/private key decryption.
	
	static CipherFactory& defaultFactory();
		/// Returns the default CipherFactory.

private:
	static int _instanceCount;

	CipherFactory(const CipherFactory&);
	CipherFactory& operator = (const CipherFactory&);
};


} } // namespace Poco::Crypto


#endif // Crypto_CipherFactory_INCLUDED
