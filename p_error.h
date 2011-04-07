/* -HEADER----------------------------------------------------------------------
UniCC LALR(1) Parser Generator 
Copyright (C) 2006-2011 by Phorward Software Technologies, Jan Max Meyer
http://unicc.phorward-software.com/ ++ unicc<<AT>>phorward-software<<DOT>>com

File:	p_error.h
Author:	Jan Max Meyer
Usage:	Error message defines

You may use, modify and distribute this software under the terms and conditions
of the Artistic License, version 2. Please see LICENSE for more information.
----------------------------------------------------------------------------- */

#ifndef P_ERROR_H
#define P_ERROR_H

#define ERRSTYLE_NONE				0
#define ERRSTYLE_FATAL				1
#define ERRSTYLE_WARNING			2
#define ERRSTYLE_FILEINFO			4
#define ERRSTYLE_STATEINFO			8
#define ERRSTYLE_LINEINFO			16
#define ERRSTYLE_PRODUCTION			32
#define ERRSTYLE_SYMBOL				64

#define ERR_MEMORY_ERROR			0
#define ERR_PARSE_ERROR				1
#define ERR_PARSE_ERROR_EXPECT		2
#define ERR_MULTIPLE_GOAL_DEF		3
#define ERR_GOAL_ONE_RHS			4
#define ERR_NO_GOAL_SYMBOL			5
#define	ERR_DOUBLE_TERMINAL_DEF		6
#define ERR_UNKNOWN_DIRECTIVE		7
#define ERR_WHITESPACE_TOKEN		8
#define ERR_UNDEFINED_NONTERM		9
#define ERR_UNDEFINED_TERM			10
#define ERR_UNUSED_NONTERM			11
#define ERR_UNUSED_TERM				12
#define ERR_REDUCE_REDUCE			13
#define ERR_SHIFT_REDUCE			14
#define ERR_KEYWORD_ANOMALY			15
#define ERR_UNKNOWN_TARGET_LANG		16
#define ERR_NO_VALUE_TYPE			17
#define ERR_ASSUMING_DEF_EOF		18
#define ERR_CMD_LINE				19
#define ERR_OPEN_OUTPUT_FILE		20
#define ERR_OPEN_INPUT_FILE			21
#define ERR_NO_GENERATOR_FILE		22
#define ERR_TAG_NOT_FOUND			23
#define ERR_XML_ERROR				24
#define ERR_XML_INCOMPLETE			25
#define ERR_DUPLICATE_ESCAPE_SEQ	26
#define ERR_CIRCULAR_DEFINITION		27
#define ERR_EMPTY_RECURSION			28
#define ERR_USELESS_RULE			29
#define ERR_NO_EFFECT_IN_MODE		30
#define ERR_NONTERM_WS_NOT_ALLOWED	31
#define ERR_INVALID_CHAR_UNIVERSE	32
#define ERR_CHARCLASS_OVERLAP		33
#define ERR_UNDEFINED_SYMREF		34
#define ERR_NO_TARGET_LANG_SUPPLY	35
#define ERR_DIRECTIVE_ALREADY_USED	36

#define OUT_OF_MEMORY				p_error( (PARSER*)NULL, ERR_MEMORY_ERROR,\
										ERRSTYLE_FATAL, __FILE__, __LINE__ ), \
									exit( EXIT_FAILURE )
#endif
