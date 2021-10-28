#pragma once

#include <iostream>
#include <string>
/*	Usage:
 *	First declare the message severity level
 *	(can be changed later)
 *	plslog::SEVERITY plslog::level = plslog::SEVERITY::INFO;
 *
 *	plslog::comment/info/data/warning/error("Your string")("on")("separate")("lines");
 *	plslog::info("Your string") << "This" << "is" << "the" << "next" << "line\n"
 *	plslog::error("Something is wrong") << 0 << 123.44f << '\n'
 */
class plslog {

	enum class SEVERITY { COMMENT, INFO, DATA, WARNING, ERROR, SILENT};
	public:
		static plslog comment(const std::string& str, std::ostream& os = std::cout) { return  plslog(SEVERITY::COMMENT, os)(str); }
		static plslog info(const std::string& str, std::ostream& os = std::cout) { return  plslog(SEVERITY::INFO, os)(str); }
		static plslog data(const std::string& str, std::ostream& os = std::cout) { return  plslog(SEVERITY::DATA, os)(str); }
		static plslog warning(const std::string& str, std::ostream& os = std::cout) { return  plslog(SEVERITY::WARNING, os)(str); }
		static plslog error(const std::string& str, std::ostream& os = std::cout) { return  plslog(SEVERITY::ERROR, os)(str); }

		template <typename T>
		const plslog& operator()(T& printable) const {

			if(message_level_ == plslog::SEVERITY::COMMENT)
				os_ << printable << '\n';

			if(message_level_ >= level) {
				if(message_level_ == plslog::SEVERITY::INFO)
					os_ << printable << "\033[0m\n";
				if(message_level_ == plslog::SEVERITY::DATA)
					os_ << "\033[1;32m" << printable << "\033[0m\n";
				if(message_level_ == plslog::SEVERITY::WARNING)
					os_ << "\033[1;33m" << printable << "\033[0m\n";
				if(message_level_ == plslog::SEVERITY::ERROR)
					os_ << "\033[1;31m" << printable << "\033[0m\n";
			}
				
			return *this;
		}

		template <typename T>
		const plslog& operator<<(T& printable) const {

			if(message_level_ == plslog::SEVERITY::COMMENT)
				os_ << printable;

			if(message_level_ >= level) {
				if(message_level_ == plslog::SEVERITY::INFO)
					os_ << printable << "\033[0m";
				if(message_level_ == plslog::SEVERITY::DATA)
					os_ << "\033[1;32m" << printable << "\033[0m";
				if(message_level_ == plslog::SEVERITY::WARNING)
					os_ << "\033[1;33m" << printable << "\033[0m";
				if(message_level_ == plslog::SEVERITY::ERROR)
					os_ << "\033[1;31m" << printable << "\033[0m";
			}
				
			return *this;
		}

	private:
		plslog(SEVERITY message_level, std::ostream& os) : message_level_(message_level), os_(os) {
			
			if(message_level_ >= level) {
				if(message_level_ == plslog::SEVERITY::INFO)
					os_ <<  "INFO: ";
				if(message_level_ == plslog::SEVERITY::DATA)
					os_ << "\033[1;32m" << "DATA: ";
				if(message_level_ == plslog::SEVERITY::WARNING)
					os_ << "\033[1;33m" << "WARNING: ";
				if(message_level_ == plslog::SEVERITY::ERROR)
					os_ << "\033[1;4;31m" << "ERROR:\033[0m ";
			}
		}

	private:
		std::ostream& os_;
		plslog::SEVERITY message_level_;
		static SEVERITY level;

};
