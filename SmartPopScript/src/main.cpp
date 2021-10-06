#include "common.h"
#include "script.h"
#include "parser.h"
#include "langdata.h"

int main(int argc, char** argv)
{
	parser::init_builtin_tokens();

	ScriptToken stoken = ScriptToken::Blue;
	DataType type = lang::get_type(stoken);

	parser::Token token = parser::Token::type(lang::get_type(stoken));

	token = parser::get_builtin_token("if");

	/*ScriptToken token = ScriptToken::Blue;

	bool is = codes::is_not_action(token);

	ScriptField field = ScriptField::constant(10);

	parser::CodeReader reader = "code.txt"_p;

	for (auto elem = reader.next(); elem; elem = reader.next())
		std::cout << elem.character;
	std::cout << std::endl;*/

	return 0;
}
