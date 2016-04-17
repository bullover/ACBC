#include "ACBCError.h"
#include <sstream>


ACBCError::ACBCError(const ACBCError::Error_t Type,
									 const std::string& rWho,
									 const std::string& rWhat) noexcept
	: m_Type(Type), m_Who(rWho), m_What(rWhat)
{}

std::string ACBCError::What() const noexcept
{
	std::stringstream ss;
	ss << m_Who << "::"
		 << (Error_t::WARNING == m_Type ? "WARNING::" : "ERROR::")
		 << m_What;
	return ss.str();
}


