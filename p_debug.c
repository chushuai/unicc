/* -MODULE----------------------------------------------------------------------
UniCC LALR(1) Parser Generator 
Copyright (C) 2006-2009 by Phorward Software Technologies, Jan Max Meyer
http://www.phorward-software.com ++ mail@phorward-software.com

File:	p_debug.c
Author:	Jan Max Meyer
Usage:	Debug and trace functionalities
----------------------------------------------------------------------------- */

/*
 * Includes
 */
#include "p_global.h"
#include "p_proto.h"
#include "p_error.h"

/*
 * Global variables
 */
extern	BOOLEAN		first_progress;

/*
 * Functions
 */

/* -FUNCTION--------------------------------------------------------------------
	Function:		p_print_symbol()
	
	Author:			Jan Max Meyer
	
	Usage:			Prints a single symbol.
					
	Parameters:		FILE*		stream				The stream where to dump the
													grammar to. If this is
													(FILE*)NULL, output is written
													to stderr.
					SYMBOL*		sym					Symbol pointer to be printed.
													
	Returns:		void
  
	~~~ CHANGES & NOTES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Date:		Author:			Note:
----------------------------------------------------------------------------- */
void p_print_symbol( FILE* stream, SYMBOL* sym )
{
	if( !stream )
		stream = stderr;

	if( sym->type == SYM_CCL_TERMINAL )
		fprintf( stream, "\'%s\'", sym->name );
	else if( sym->type == SYM_KW_TERMINAL )
		fprintf( stream, "\"%s\"", sym->name );
	else if( sym->type == SYM_REGEX_TERMINAL )
		fprintf( stream, "@%s", sym->name );
	else if( sym->type == SYM_EXTERN_TERMINAL )
		fprintf( stream, "*%s", sym->name );
	else if( sym->type == SYM_ERROR_RESYNC )
		fprintf( stream, P_ERROR_RESYNC );
	else
		fprintf( stream, "%s", sym->name );
}

/* -FUNCTION--------------------------------------------------------------------
	Function:		p_dump_grammar()
	
	Author:			Jan Max Meyer
	
	Usage:			Dumps the analyzed grammar and all its symbols to a desired
					file or stream in an ASCII-based view.
					
	Parameters:		FILE*		stream				The stream where to dump the
													grammar to. If this is
													(FILE*)NULL, output is written
													to stderr.
					PARSER*		parser				Parser information structure
													pointer.
													
	Returns:		void
  
	~~~ CHANGES & NOTES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Date:		Author:			Note:
----------------------------------------------------------------------------- */
void p_dump_grammar( FILE* stream, PARSER* parser )
{
	LIST*		i		= (LIST*)NULL;
	LIST*		j		= (LIST*)NULL;
	LIST*		k		= (LIST*)NULL;
	
	SYMBOL*		s		= (SYMBOL*)NULL;
	SYMBOL*		sf		= (SYMBOL*)NULL;
	SYMBOL*		sym		= (SYMBOL*)NULL;
	PROD*		p		= (PROD*)NULL;
	
	if( !stream )
		stream = stderr;

	if( first_progress )
		fprintf( stream, "\n" );

	fprintf( stream, "\n--- %s%sGrammar ---\n",
		( parser->p_name ? parser->p_name : "" ),
			( parser->p_name ? " " : "" ) );

	
	for( i = parser->symbols; i; i = i->next )
	{
		fprintf( stream, "    " );

		s = i->pptr;
		if( 1 || s->type == SYM_NON_TERMINAL )
		{
			fprintf( stream, "(%d) ", s->id );
			p_print_symbol( stream, s );
			fprintf( stream, " " );
			
			/* Printing the FIRST-set */
			fprintf( stream, "[ " );
			for( j = s->first; j; j = j->next )
			{
				sym = j->pptr;
				
				p_print_symbol( stream, sym );
				fprintf( stream, " " );
			}
						
			if( s->type == SYM_NON_TERMINAL )
			{
				fprintf( stream, "] lexem:%d prec:%d assoc:%c v:%s\n", s->lexem,
					s->prec, ( ( s->assoc == ASSOC_LEFT ) ? 'L' :
					( ( s->assoc == ASSOC_RIGHT ) ? 'R' : 'N' ) ),
						( s->vtype ) ? s->vtype->int_name : "(null)" );

				/* Printing the productions */
				for( j = s->productions; j; j = j->next )
				{
					p = j->pptr;
					fprintf( stream, "    (%d) -> ", p->id );
					p_dump_production( stream, p, FALSE, FALSE );
				}
			}
			else
			{
				fprintf( stream, "] prec:%d assoc:%c\n",
					s->prec, ( ( s->assoc == ASSOC_LEFT ) ? 'L' :
					( ( s->assoc == ASSOC_RIGHT ) ? 'R' : 'N' ) ) );
			}

			fprintf( stream, "\n" );
		}
	}

	first_progress = FALSE;
}

/* -FUNCTION--------------------------------------------------------------------
	Function:		p_dump_item_set()
	
	Author:			Jan Max Meyer
	
	Usage:			Dumps an item set.
					
	Parameters:		FILE*		stream				The stream where to dump the
													grammar to. If this is
													(FILE*)NULL, output is written
													to stderr.
					uchar*		title				The title of the item set.
					LIST*		list				The item set linked-list
													itself.

	Returns:		void
  
	~~~ CHANGES & NOTES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Date:		Author:			Note:
----------------------------------------------------------------------------- */
void p_dump_item_set( FILE* stream, uchar* title, LIST* list )
{
	ITEM*		it		= (ITEM*)NULL;
	LIST*		i		= (LIST*)NULL;
	LIST*		j		= (LIST*)NULL;
	SYMBOL*		sym		= (SYMBOL*)NULL;
	int			cnt		= 0;
	
	if( !stream )
		stream = stderr;

	if( list != (LIST*)NULL )
	{
		/* if( first_progress )
			fprintf( stream, "\n\n" ); */

		if( title )
			fprintf( stream, "\n%s\n", title );
		
		for( i = list; i; i = i->next )
		{			
			it = i->pptr;
			
			
			fprintf( stream, "    (%d) %s -> ",
				it->prod->id, it->prod->lhs->name );
			
			cnt = 0;
			for( j = it->prod->rhs; j; j = j->next )
			{
				sym = j->pptr;
				
				if( cnt == it->dot_offset )
					fprintf( stream, "." );

				p_print_symbol( stream, sym );
				fprintf( stream, " " );

				cnt++;
			}

			if( cnt == it->dot_offset )
			{
				fprintf( stream, "." );
				fprintf( stream, "      { " );
				for( j = it->lookahead; j; j = j->next )
				{
					sym = j->pptr;
					p_print_symbol( stream, sym );
					fprintf( stream, " " );
				}
				fprintf( stream, "}" );
			}

			fprintf( stream, "\n" );
		}
	}

	first_progress = FALSE;
}


/* -FUNCTION--------------------------------------------------------------------
	Function:		p_dump_map()
	
	Author:			Jan Max Meyer
	
	Usage:			Dumps a bit map.
					
	Parameters:		FILE*		stream				The stream where to dump the
													grammar to. If this is
													(FILE*)NULL, output is written
													to stderr.
					bitset		map					The bit map to be printed.
					int			map_size			Maximum size of the map.

	Returns:		void
  
	~~~ CHANGES & NOTES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Date:		Author:			Note:
----------------------------------------------------------------------------- */
void p_dump_map( FILE* stream, bitset map, int map_size )
{
	int i;

	if( !stream )
		stream = stderr;

	if( first_progress )
		fprintf( stream, "\n\n" );

	for( i = 0; i < map_size; i++ )
	{
		if( i % 10 == 0 )
			fprintf( stream, "\n" );
		fprintf( stream, "%03d:%d ", i, ( bitset_get( map, i ) ? 1 : 0 ) );
	}

	fprintf( stream, "\n" );

	first_progress = FALSE;
}


/* -FUNCTION--------------------------------------------------------------------
	Function:		p_dump_lalr_states()
	
	Author:			Jan Max Meyer
	
	Usage:			Dumps the LALR(1) states.
					
	Parameters:		FILE*		stream				The stream where to dump the
													grammar to. If this is
													(FILE*)NULL, output is written
													to stdout.
					PARSER*		parser				Parser information structure.

	Returns:		void
  
	~~~ CHANGES & NOTES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Date:		Author:			Note:
----------------------------------------------------------------------------- */
void p_dump_lalr_states( FILE* stream, PARSER* parser )
{
	LIST*	l;
	STATE*	st;

	if( !stream )
		stream = stderr;

	if( first_progress )
		fprintf( stream, "\n\n" );
	first_progress = FALSE;

	for( l = parser->lalr_states; l; l = l->next )
	{
		st = (STATE*)(l->pptr);
		
		fprintf( stream, "  --- State %d ---\n", st->state_id );
		p_dump_item_set( stream, "Kernel:", st->kernel );
		p_dump_item_set( stream, "Epsilon:", st->epsilon );
		fprintf( stream, "\n" );
	}
}

/* -FUNCTION--------------------------------------------------------------------
	Function:		p_dump_productions()
	
	Author:			Jan Max Meyer
	
	Usage:			Dumps all productions.
					
	Parameters:		FILE*		stream				The stream where to dump the
													productions to. If this is
													(FILE*)NULL, output is written
													to stderr.
					PARSER*		parser				Parser information structure
													pointer.
													
	Returns:		void
  
	~~~ CHANGES & NOTES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Date:		Author:			Note:
----------------------------------------------------------------------------- */
void p_dump_productions( FILE* stream, PARSER* parser )
{
	LIST*		l		= (LIST*)NULL;
	LIST*		m		= (LIST*)NULL;
	LIST*		n		= (LIST*)NULL;
	SYMBOL*		s		= (SYMBOL*)NULL;
	PROD*		p;

	if( !stream )
		stream = stderr;

	if( first_progress )
		fprintf( stream, "\n" );
	fprintf( stream, "--- %s%sProductions ---\n",
		( parser->p_name ? parser->p_name : "" ),
			( parser->p_name ? " " : "" ) );
	
	for( l = parser->productions; l; l = l->next )
	{
		p = (PROD*)( l->pptr );
	
		p_dump_production( stream, p, TRUE, TRUE );

		fprintf( stream, "\n" );
	}

	first_progress = FALSE;
}

/* -FUNCTION--------------------------------------------------------------------
	Function:		p_dump_production()
	
	Author:			Jan Max Meyer
	
	Usage:			Dumps one production.
					
	Parameters:		FILE*		stream				The stream where to dump the
													productions to. If this is
													(FILE*)NULL, output is written
													to stderr.
					PROD*		prod				Pointer to the production
													to be printed.
					BOOLEAN		with_lhs			Prints production's lhs and
													a "->" between rhs
					BOOLEAN		semantics			If TRUE, production-related
													semantics are even printed.
													
	Returns:		void
  
	~~~ CHANGES & NOTES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Date:		Author:			Note:
----------------------------------------------------------------------------- */
void p_dump_production( FILE* stream, PROD* p,
	BOOLEAN with_lhs, BOOLEAN semantics )
{
	LIST*	l			= p->rhs;
	LIST*	m			= p->rhs_idents;
	BOOLEAN	embedded 	= FALSE;
	SYMBOL*	sym;
	uchar*	ident;

	if( !stream )
		stream = stderr;

	if( with_lhs )
		fprintf( stream, "    (%d) %s -> ", p->id, p->lhs->name );
		
	if( semantics && p->sem_rhs )
	{
		l = p->sem_rhs;
		m = p->sem_rhs_idents;
		
		embedded = TRUE;
	}

	for( ; l && m; l = list_next( l ), m = list_next( m ))
	{
		if( embedded && list_count( l ) > list_count( p->rhs ) )
			fprintf( stream, "<<" );
		else
		{
			sym = (SYMBOL*)( l->pptr );
			p_print_symbol( stream, sym );
		}

		ident = (char*)( m->pptr );
		if( semantics && ident )
			fprintf( stream, ":%s", ident );
		
		fprintf( stream, " " );
	}

	if( p->code && semantics )
		fprintf( stream, " [*%s*]", p->code );

	fprintf( stream, "\n" );
}

