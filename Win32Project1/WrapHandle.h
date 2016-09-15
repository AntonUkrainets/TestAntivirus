
#pragma once
#include <windows.h>
#include <string>
#include <memory>

namespace Test
{

	class IHandle
	{

	protected:

		HANDLE h;

		IHandle(const IHandle&) = delete;

		const IHandle & operator =(const IHandle&) = delete;

	public:

		IHandle(HANDLE h = nullptr) : h(h){ }

		virtual	~IHandle(void)
		{

			if (IHandle::h)
				::CloseHandle(IHandle::h);

		}

		virtual operator HANDLE	(void)	const throw()
		{
			return this->h;
		}

		virtual bool operator ! (void)	const throw() = 0;

		virtual HANDLE Release(void) throw()
		{

			HANDLE h = this->h;

			this->h = nullptr;

			return h;

		}

	};

	// Обертка для хранения дескриптора потока
	class HandleThread : public IHandle
	{

		HandleThread(const HandleThread&) = delete;

		const HandleThread & operator =(const HandleThread&) = delete;

	public:

		HandleThread(HANDLE h = nullptr) : IHandle(h){}
		
		virtual ~HandleThread(void){}
		
		bool operator ! (void)	const throw() override
		{
			return IHandle::h == nullptr;
		}

	};

	// Обертка для хранения дескриптора Windows Crypto Provider и гарантированного освобождения
	class HandleWinCryptoProvider
	{

	protected:

		HCRYPTPROV h;

	public:

		HandleWinCryptoProvider(HCRYPTPROV h = 0) : h(h){ }

		virtual ~HandleWinCryptoProvider(void)
		{
			if (this->h)
				::CryptReleaseContext(this->h, 0);
		}

		operator ULONG_PTR (void) const throw()
		{
			return this->h;
		}

		operator ULONG_PTR* (void) throw()
		{
			return &this->h;
		}

	};

	// Обертка для хранения дескриптора Windows Crypto Hash и гарантированного освобождения
	class HandleWinCryptoHash : public HandleWinCryptoProvider
	{

	public:

		HandleWinCryptoHash(HCRYPTHASH hHash = 0) : HandleWinCryptoProvider(hHash){ }

		virtual ~HandleWinCryptoHash(void)
		{

			if (HandleWinCryptoProvider::h)
				::CryptDestroyHash(HandleWinCryptoProvider::h);

			HandleWinCryptoProvider::h = 0;

		}

	};

}