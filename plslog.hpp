#pragma once

#include <iostream>
#include <string>
/*	Usage:
 *	First declare the message severity level
 *	(can be changed later)
 *	plslog::levels plslog::level = plslog::levels::INFO;
 *
 *	plslog::comment/info/data/warning/error("Your string")("with")("spaces")(0.3f);
 *	plslog::info("Your string") << "without" << "spaces" << 0.3f << "\n"
 */
class plslog {

	public:
		enum class levels { COMMENT, INFO, DATA, WARNING, ERROR, SILENT};
		static levels global_level;

		static plslog comment(const std::string& str) { return plslog(levels::COMMENT)(str); }
		static plslog info(const std::string& str) { return plslog(levels::INFO)(str); }
		static plslog data(const std::string& str) { return plslog(levels::DATA)(str); }
		static plslog warning(const std::string& str) { return plslog(levels::WARNING)(str); }
		static plslog error(const std::string& str) { return plslog(levels::ERROR)(str); }

		static void set_level(levels new_level) { global_level = new_level; }

		template <typename T>
		const plslog& operator()(T& printable) const {

			if(message_level_ == plslog::levels::COMMENT)
				std::cout << printable << ' ';

			if(message_level_ >= global_level) {
				if(message_level_ == plslog::levels::INFO)
					std::cout << printable << "\033[0m ";
				if(message_level_ == plslog::levels::DATA)
					std::cout << "\033[1;32m" << printable << "\033[0m ";
				if(message_level_ == plslog::levels::WARNING)
					std::cout << "\033[1;33m" << printable << "\033[0m ";
				if(message_level_ == plslog::levels::ERROR)
					std::cout << "\033[1;31m" << printable << "\033[0m ";
			}
				
			return *this;
		}

		template <typename T>
		const plslog& operator<<(T& printable) const {

			if(message_level_ == plslog::levels::COMMENT)
				std::cout << printable;

			if(message_level_ >= global_level) {
				if(message_level_ == plslog::levels::INFO)
					std::cout << printable << "\033[0m";
				if(message_level_ == plslog::levels::DATA)
					std::cout << "\033[1;32m" << printable << "\033[0m";
				if(message_level_ == plslog::levels::WARNING)
					std::cout << "\033[1;33m" << printable << "\033[0m";
				if(message_level_ == plslog::levels::ERROR)
					std::cout << "\033[1;31m" << printable << "\033[0m";
			}
				
			return *this;
		}

	private:
		plslog(levels message_level = levels::COMMENT) : message_level_(message_level) {
			
			if(message_level_ >= global_level) {
				if(message_level_ == plslog::levels::INFO)
					std::cout <<  "INFO: ";
				if(message_level_ == plslog::levels::DATA)
					std::cout << "\033[1;32m" << "DATA: ";
				if(message_level_ == plslog::levels::WARNING)
					std::cout << "\033[1;33m" << "WARNING: ";
				if(message_level_ == plslog::levels::ERROR)
					std::cout << "\033[1;4;31m" << "ERROR:\033[0m ";
			}
		}
	private:
		levels message_level_;
};
