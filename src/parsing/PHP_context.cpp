/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Parser context for the PHP parser 
 */

#include "PHP_context.h"

PHP_context::PHP_context(std::istream& input, String* filename)
: stream (input)
{	
	init_scanner(NULL);

	php_script = NULL;
	current_method = new String("");
	current_class = new String("");

	this->filename = filename;
	source_line = 1;
	mt_index = 0;
	mt_count = 0;
	last_commented_node = NULL;
	hash_bang = NULL;
	
	attach_to_previous = false;
	after_arrow = false;
	starts_line = true;

	heredoc_attr = NULL;
}

int PHP_lex (YYSTYPE* yylval, void* scanner);
int PHP_parse (PHP_context* context);
int PHP_dot_parse (PHP_context* context);

bool
PHP_context::lex ()
{
	return PHP_lex (mt_lval, scanner);
}

bool
PHP_context::parse ()
{
	return PHP_parse (this) == 0;
}

bool
PHP_context::dump_parse_tree ()
{
	last_commented_node = new AST::Class_def (NULL, NULL, NULL, NULL, NULL);
	std::cout
	<< "/*\n"
	<< " * Parse tree in dot format generated by phc -- the PHP compiler\n"
	<< " */\n"
	<< "\n"
	<< "digraph AST {\n"
	<< "ordering=out;\n"
	;

	bool result = (PHP_dot_parse (this) == 0);

	std::cout << "}" << std::endl;

	return result;
}

PHP_context::~PHP_context()
{
	destroy_scanner();
}
