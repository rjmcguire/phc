/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Translate the shredded and lowered AST to HIR 
 */

#ifndef PHC_HIR_TO_MIR_H
#define PHC_HIR_TO_MIR_H

#include "HIR_fold.h"
#include "MIR.h"
#include "process_ir/General.h"

/*
 * Those AST nodes that should no longer appear in the HIR do not have an
 * implementation in this translation, so that we inherit the default assert(0)
 * implementation from AST_fold. However, to satisfy the typechecker, we must
 * still provide a reasonble type for these nodes. For example, the type we
 * specify for For (which does not have a corresponding HIR construct) is
 * simplify HIR::Statement*. For some constructs, specifying HIR::Node*
 * suffices.
 */
class HIR_to_MIR : public HIR::Fold
<MIR::Node*,				// Node*
 MIR::PHP_script*,			// PHP_script*
 MIR::Statement*,			// Statement*
 MIR::Class_def*,			// Class_def*
 MIR::Class_mod*,			// Class_mod*
 MIR::Interface_def*,		// Interface_def*
 MIR::Member*,				// Member*
 MIR::Method*,				// Method*
 MIR::Signature*,			// Signature*
 MIR::Method_mod*,			// Method_mod*
 MIR::Formal_parameter*,	// Formal_parameter*
 MIR::Type*,				// Type*
 MIR::Attribute*,			// Attribute*
 MIR::Attr_mod*,			// Attr_mod*
 MIR::Name_with_default*,	// Name_with_default*
 MIR::Statement*,			// If*
 MIR::Statement*,			// While*
 MIR::Statement*,			// Foreach*
 MIR::Statement*,			// Switch*
 MIR::Node*,				// Switch_case*
 MIR::Statement*,			// Break*
 MIR::Statement*,			// Continue*
 MIR::Return*,				// Return*
 MIR::Static_declaration*,	// Static_declaration*
 MIR::Global*,				// Global*
 MIR::Statement*,			// Declare*
 MIR::Node*,				// Directive*
 MIR::Try*,					// Try*
 MIR::Catch*,				// Catch*
 MIR::Throw*,				// Throw*
 MIR::Eval_expr*,			// Eval_expr*
 MIR::Statement*,			// Nop*
 MIR::Branch*,				// Branch*
 MIR::Goto*,				// Goto*
 MIR::Label*,				// Label*
 MIR::Foreach_reset*,	// Foreach_reset*
 MIR::Foreach_next*,	// Foreach_next*
 MIR::Foreach_end*,	// Foreach_end*
 MIR::Foreach_has_key*,	// Foreach_has_key*
 MIR::Foreach_get_key*,	// Foreach_get_key*
 MIR::Foreach_get_val*,	// Foreach_get_val*
 MIR::Expr*,				// Expr*
 MIR::Literal*,				// Literal*
 MIR::Assignment*,			// Assignment*
 MIR::Expr*,				// Op_assignment*
 MIR::Expr*,				// List_assignment*
 MIR::Node*,				// List_element*
 MIR::Node*,				// Nested_list_elements*
 MIR::Cast*,				// Cast*
 MIR::Unary_op*,			// Unary_op*
 MIR::Bin_op*,				// Bin_op*
 MIR::Expr*,				// Conditional_expr*
 MIR::Expr*,				// Ignore_errors*
 MIR::Constant*,			// Constant*
 MIR::Instanceof*,			// Instanceof*
 MIR::Variable*,			// Variable*
 MIR::Variable_name*,		// Variable_name*
 MIR::Reflection*,			// Reflection*
 MIR::Target*,				// Target*
 MIR::Pre_op*,				// Pre_op*
 MIR::Expr*,				// Post_op*
 MIR::Array*,				// Array*
 MIR::Array_elem*,			// Array_elem*
 MIR::Method_invocation*,	// Method_invocation*
 MIR::Method_name*,			// Method_name*
 MIR::Actual_parameter*,	// Actual_parameter*
 MIR::New*,					// New*
 MIR::Class_name*,			// Class_name*
 MIR::Node*,				// Commented_node*
 MIR::Identifier*,			// Identifier*
 MIR::HT_ITERATOR*,		// HT_ITERATOR*
 MIR::CLASS_NAME*,		// CLASS_NAME*
 MIR::INTERFACE_NAME*,	// INTERFACE_NAME*
 MIR::METHOD_NAME*,		// METHOD_NAME*
 MIR::VARIABLE_NAME*,		// VARIABLE_NAME*
 MIR::Identifier*,			// DIRECTIVE_NAME*
 MIR::LABEL_NAME*,		// LABEL_NAME*
 MIR::INT*,				// INT*
 MIR::REAL*,				// REAL*
 MIR::STRING*,			// STRING*
 MIR::BOOL*,				// BOOL*
 MIR::NIL*,				// NIL*
 MIR::OP*,				// OP*
 MIR::CAST*,				// CAST*
 MIR::CONSTANT_NAME*>		// CONSTANT_NAME*
{
	MIR::PHP_script* fold_impl_php_script(HIR::PHP_script* orig, List<MIR::Statement*>* statements) 
	{
		MIR::PHP_script* result;
		result = new MIR::PHP_script(statements);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Class_def* fold_impl_class_def(HIR::Class_def* orig, MIR::Class_mod* class_mod, MIR::CLASS_NAME* class_name, MIR::CLASS_NAME* extends, List<MIR::INTERFACE_NAME*>* implements, List<MIR::Member*>* members) 
	{
		MIR::Class_def* result;
		result = new MIR::Class_def(class_mod, class_name, extends, implements, members);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Class_mod* fold_impl_class_mod(HIR::Class_mod* orig, bool is_abstract, bool is_final) 
	{
		MIR::Class_mod* result;
		result = new MIR::Class_mod(is_abstract, is_final);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Interface_def* fold_impl_interface_def(HIR::Interface_def* orig, MIR::INTERFACE_NAME* interface_name, List<MIR::INTERFACE_NAME*>* extends, List<MIR::Member*>* members) 
	{
		MIR::Interface_def* result;
		result = new MIR::Interface_def(interface_name, extends, members);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Method* fold_impl_method(HIR::Method* orig, MIR::Signature* signature, List<MIR::Statement*>* statements) 
	{
		MIR::Method* result;
		result = new MIR::Method(signature, statements);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Signature* fold_impl_signature(HIR::Signature* orig, MIR::Method_mod* method_mod, bool is_ref, MIR::METHOD_NAME* method_name, List<MIR::Formal_parameter*>* formal_parameters) 
	{
		MIR::Signature* result;
		result = new MIR::Signature(method_mod, is_ref, method_name, formal_parameters);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Method_mod* fold_impl_method_mod(HIR::Method_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_abstract, bool is_final) 
	{
		MIR::Method_mod* result;
		result = new MIR::Method_mod(is_public, is_protected, is_private, is_static, is_abstract, is_final);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Formal_parameter* fold_impl_formal_parameter(HIR::Formal_parameter* orig, MIR::Type* type, bool is_ref, MIR::Name_with_default* var) 
	{
		MIR::Formal_parameter* result;
		result = new MIR::Formal_parameter(type, is_ref, var);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Type* fold_impl_type(HIR::Type* orig, MIR::CLASS_NAME* class_name) 
	{
		MIR::Type* result;
		result = new MIR::Type(class_name);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Attribute* fold_impl_attribute(HIR::Attribute* orig, MIR::Attr_mod* attr_mod, List<MIR::Name_with_default*>* vars) 
	{
		assert(vars->size() == 1);

		MIR::Attribute* result;
		result = new MIR::Attribute(attr_mod, vars->front());
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Attr_mod* fold_impl_attr_mod(HIR::Attr_mod* orig, bool is_public, bool is_protected, bool is_private, bool is_static, bool is_const) 
	{
		MIR::Attr_mod* result;
		result = new MIR::Attr_mod(is_public, is_protected, is_private, is_static, is_const);
		result->attrs = orig->attrs;
		return result;
	}
	
	MIR::Name_with_default* fold_impl_name_with_default(HIR::Name_with_default* orig, MIR::VARIABLE_NAME* variable_name, MIR::Expr* expr) 
	{ 
		MIR::Name_with_default* result;
		result = new MIR::Name_with_default(variable_name, expr);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Return* fold_impl_return(HIR::Return* orig, MIR::Expr* expr) 
	{
		MIR::Return* result;
		result = new MIR::Return(expr);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Static_declaration* fold_impl_static_declaration(HIR::Static_declaration* orig, List<MIR::Name_with_default*>* vars) 
	{
		assert(vars->size() == 1);

		MIR::Static_declaration* result;
		result = new MIR::Static_declaration(vars->front());
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Global* fold_impl_global(HIR::Global* orig, List<MIR::Variable_name*>* variable_names) 
	{
		// MIR only takes a single variable per global; should be been taken care of in the shredder
		assert(variable_names->size() == 1);
		
		MIR::Global* result;
		result = new MIR::Global(variable_names->front());
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Try* fold_impl_try(HIR::Try* orig, List<MIR::Statement*>* statements, List<MIR::Catch*>* catches) 
	{
		MIR::Try* result;
		result = new MIR::Try(statements, catches);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Catch* fold_impl_catch(HIR::Catch* orig, MIR::CLASS_NAME* class_name, MIR::VARIABLE_NAME* variable_name, List<MIR::Statement*>* statements) 
	{
		MIR::Catch* result;
		result = new MIR::Catch(class_name, variable_name, statements);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Throw* fold_impl_throw(HIR::Throw* orig, MIR::Expr* expr) 
	{
		MIR::Throw* result;
		result = new MIR::Throw(expr);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Eval_expr* fold_impl_eval_expr(HIR::Eval_expr* orig, MIR::Expr* expr) 
	{
		MIR::Eval_expr* result;
		result = new MIR::Eval_expr(expr);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Branch* fold_impl_branch(HIR::Branch* orig, MIR::Expr* expr, MIR::LABEL_NAME* iftrue, MIR::LABEL_NAME* iffalse) 
	{
		MIR::Branch* result;
		result = new MIR::Branch(expr, iftrue, iffalse);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Goto* fold_impl_goto(HIR::Goto* orig, MIR::LABEL_NAME* label_name) 
	{
		MIR::Goto* result;
		result = new MIR::Goto(label_name);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Label* fold_impl_label(HIR::Label* orig, MIR::LABEL_NAME* label_name) 
	{
		MIR::Label* result;
		result = new MIR::Label(label_name);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Foreach_reset* fold_impl_foreach_reset (HIR::Foreach_reset* orig, MIR::Variable* variable, MIR::HT_ITERATOR* ht_iterator) 
	{
		MIR::Foreach_reset* result;
		result = new MIR::Foreach_reset (var_name_from_expr (variable), ht_iterator);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Foreach_next* fold_impl_foreach_next (HIR::Foreach_next* orig, MIR::Variable* variable, MIR::HT_ITERATOR* ht_iterator) 
	{
		MIR::Foreach_next* result;
		result = new MIR::Foreach_next (var_name_from_expr (variable), ht_iterator);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Foreach_end* fold_impl_foreach_end (HIR::Foreach_end* orig, MIR::Variable* variable, MIR::HT_ITERATOR* ht_iterator) 
	{
		MIR::Foreach_end* result;
		result = new MIR::Foreach_end (var_name_from_expr (variable), ht_iterator);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Foreach_has_key* fold_impl_foreach_has_key (HIR::Foreach_has_key* orig, MIR::Variable* variable, MIR::HT_ITERATOR* ht_iterator) 
	{
		MIR::Foreach_has_key* result;
		result = new MIR::Foreach_has_key (var_name_from_expr (variable), ht_iterator);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Foreach_get_key* fold_impl_foreach_get_key (HIR::Foreach_get_key* orig, MIR::Variable* variable, MIR::HT_ITERATOR* ht_iterator) 
	{
		MIR::Foreach_get_key* result;
		result = new MIR::Foreach_get_key (var_name_from_expr (variable), ht_iterator);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Foreach_get_val* fold_impl_foreach_get_val (HIR::Foreach_get_val* orig, MIR::Variable* variable, MIR::HT_ITERATOR* ht_iterator) 
	{
		MIR::Foreach_get_val* result;
		result = new MIR::Foreach_get_val (var_name_from_expr (variable), ht_iterator);
		result->attrs = orig->attrs;
		return result;
	}
	
	MIR::Assignment* fold_impl_assignment(HIR::Assignment* orig, MIR::Variable* variable, bool is_ref, MIR::Expr* expr) 
	{
		MIR::Assignment* result;
		result = new MIR::Assignment(variable, is_ref, expr);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::VARIABLE_NAME* var_name_from_expr (MIR::Expr* expr)
	{
		if (expr == NULL) // $x[]
			return NULL;

		MIR::Variable* var = dynamic_cast<MIR::Variable*> (expr);
		assert (var);
		assert (var->array_indices->size () == 0);
		MIR::Variable_name* var_name = var->variable_name;
		assert (var_name);
		MIR::VARIABLE_NAME* token = dynamic_cast<MIR::VARIABLE_NAME*> (var_name);
		assert (token);
		return token;
	}

	MIR::Cast* fold_impl_cast(HIR::Cast* orig, MIR::CAST* cast, MIR::Expr* expr) 
	{
		MIR::Cast* result;
		result = new MIR::Cast(cast, var_name_from_expr (expr));
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Unary_op* fold_impl_unary_op(HIR::Unary_op* orig, MIR::OP* op, MIR::Expr* expr) 
	{
		MIR::Unary_op* result;
		result = new MIR::Unary_op(op, var_name_from_expr (expr));
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Bin_op* fold_impl_bin_op(HIR::Bin_op* orig, MIR::Expr* left, MIR::OP* op, MIR::Expr* right) 
	{
		MIR::Bin_op* result;
		result = new MIR::Bin_op(var_name_from_expr (left), op, var_name_from_expr (right));
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Constant* fold_impl_constant(HIR::Constant* orig, MIR::CLASS_NAME* class_name, MIR::CONSTANT_NAME* constant_name) 
	{
		MIR::Constant* result;
		result = new MIR::Constant(class_name, constant_name);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Instanceof* fold_impl_instanceof(HIR::Instanceof* orig, MIR::Expr* expr, MIR::Class_name* class_name) 
	{
		MIR::Instanceof* result;
		result = new MIR::Instanceof(var_name_from_expr (expr), class_name);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Variable* fold_impl_variable(HIR::Variable* orig, MIR::Target* target, MIR::Variable_name* variable_name, List<MIR::Expr*>* array_indices) 
	{
		MIR::Variable* result;

		List<MIR::VARIABLE_NAME*>* var_names = new List<MIR::VARIABLE_NAME*>;
		List<MIR::Expr*>::const_iterator i;
		for (i = array_indices->begin (); i != array_indices->end (); i++)
		{
			var_names->push_back (var_name_from_expr (*i));
		}

		result = new MIR::Variable(target, variable_name, var_names);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Reflection* fold_impl_reflection(HIR::Reflection* orig, MIR::Expr* expr) 
	{
		MIR::Reflection* result;
		result = new MIR::Reflection(var_name_from_expr (expr));
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Pre_op* fold_impl_pre_op(HIR::Pre_op* orig, MIR::OP* op, MIR::Variable* variable) 
	{
		MIR::Pre_op* result;
		result = new MIR::Pre_op(op, variable);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Array* fold_impl_array(HIR::Array* orig, List<MIR::Array_elem*>* array_elems) 
	{
		MIR::Array* result;
		result = new MIR::Array(array_elems);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Array_elem* fold_impl_array_elem(HIR::Array_elem* orig, MIR::Expr* key, bool is_ref, MIR::Expr* val) 
	{
		MIR::Array_elem* result;
		result = new MIR::Array_elem(key, is_ref, val);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Method_invocation* fold_impl_method_invocation(HIR::Method_invocation* orig, MIR::Target* target, MIR::Method_name* method_name, List<MIR::Actual_parameter*>* actual_parameters) 
	{
		MIR::Method_invocation* result;
		result = new MIR::Method_invocation(target, method_name, actual_parameters);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::Actual_parameter* fold_impl_actual_parameter(HIR::Actual_parameter* orig, bool is_ref, MIR::Expr* expr) 
	{
		MIR::Variable* var = dynamic_cast<MIR::Variable*> (expr);
		assert (var);

		MIR::Actual_parameter* result;
		result = new MIR::Actual_parameter(is_ref, var->target, var->variable_name, var->array_indices);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::New* fold_impl_new(HIR::New* orig, MIR::Class_name* class_name, List<MIR::Actual_parameter*>* actual_parameters) 
	{
		MIR::New* result;
		result = new MIR::New(class_name, actual_parameters);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::HT_ITERATOR* fold_ht_iterator (HIR::HT_ITERATOR* orig)
	{
		MIR::HT_ITERATOR* result;
		result = new MIR::HT_ITERATOR (orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::CLASS_NAME* fold_class_name(HIR::CLASS_NAME* orig) 
	{
		MIR::CLASS_NAME* result;
		result = new MIR::CLASS_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::INTERFACE_NAME* fold_interface_name(HIR::INTERFACE_NAME* orig) 
	{
		MIR::INTERFACE_NAME* result;
		result = new MIR::INTERFACE_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::METHOD_NAME* fold_method_name(HIR::METHOD_NAME* orig) 
	{
		MIR::METHOD_NAME* result;
		result = new MIR::METHOD_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::VARIABLE_NAME* fold_variable_name(HIR::VARIABLE_NAME* orig) 
	{
		MIR::VARIABLE_NAME* result;
		result = new MIR::VARIABLE_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::LABEL_NAME* fold_label_name(HIR::LABEL_NAME* orig) 
	{
		MIR::LABEL_NAME* result;
		result = new MIR::LABEL_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::INT* fold_int(HIR::INT* orig) 
	{
		MIR::INT* result;
		result = new MIR::INT(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::REAL* fold_real(HIR::REAL* orig) 
	{
		MIR::REAL* result;
		result = new MIR::REAL(orig->value);
		result->attrs = orig->attrs;
		result->source_rep = orig->source_rep;
		return result;
	}

	MIR::STRING* fold_string(HIR::STRING* orig) 
	{
		MIR::STRING* result;
		result = new MIR::STRING(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::BOOL* fold_bool(HIR::BOOL* orig) 
	{
		MIR::BOOL* result;
		result = new MIR::BOOL(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::NIL* fold_nil(HIR::NIL* orig) 
	{
		MIR::NIL* result;
		result = new MIR::NIL();
		result->attrs = orig->attrs;
		return result;
	}

	MIR::OP* fold_op(HIR::OP* orig) 
	{
		MIR::OP* result;
		result = new MIR::OP(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::CAST* fold_cast(HIR::CAST* orig) 
	{
		MIR::CAST* result;
		result = new MIR::CAST(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

	MIR::CONSTANT_NAME* fold_constant_name(HIR::CONSTANT_NAME* orig) 
	{
		MIR::CONSTANT_NAME* result;
		result = new MIR::CONSTANT_NAME(orig->value);
		result->attrs = orig->attrs;
		return result;
	}

 	~HIR_to_MIR () {}
};

#endif // PHC_HIR_TO_MIR_H 