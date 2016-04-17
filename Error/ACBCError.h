#ifndef ACBCERROR_H
#define ACBCERROR_H

#include <string>


class ACBCError
{
	public:
		enum class Error_t
		{
			WARNING,
			FATAL
        };

        ACBCError(const Error_t Type, const std::string& rWho,
						 const std::string& rWhat) noexcept;

		std::string What() const noexcept;

        inline const std::string& GetWho() const noexcept
		{
			return m_Who;
		}

        inline const std::string& GetWhat() const noexcept
		{
			return m_What;
		}

        inline const Error_t& GetType() const noexcept
		{
			return m_Type;
		}

	private:
		const Error_t m_Type;
		const std::string m_Who;
		const std::string m_What;
};



#endif // ACBCERROR_H
