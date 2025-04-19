#ifndef CONFIGURER_CORE
#define CONFIGURER_CORE

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

typedef uint32_t color_rgba;

#define DEFAULT_PACKAGE_LIST_SIZE 32

#define CONFIGURE( ... ) \
char **package_list;                                            \
size_t num_packages;                                            \
size_t size_packages;                                           \
FILE *creation_log; \
                                                                \
int main(void) {                                                \
	creation_log = fopen( "./creation_log.txt", "w" );\
	package_list = calloc(DEFAULT_PACKAGE_LIST_SIZE, sizeof(char*));\
	num_packages = 0;                                               \
	size_packages = DEFAULT_PACKAGE_LIST_SIZE;                      \
	                                                                \
	                                                                \
	__VA_ARGS__                                                     \
\
\
	FILE *packages_script = fopen("./manage_packages.sh", "w");          \
	fprintf( packages_script, "yay --needed -S ");\
	for( int i = 0; i < num_packages; ++i) { \
		fprintf(packages_script, "%s ", package_list[i] ); \
	} \
 \
	fprintf( packages_script, "\nyay -D --asdeps $(yay -Qqe)\n"); \
	fprintf( packages_script, "yay -D --asexplicit ");\
	for( int i = 0; i < num_packages; ++i) { \
		fprintf(packages_script, "%s ", package_list[i] ); \
	} \
	fprintf( packages_script, "\nyay -Qdtq | yay -Rns -\n" );\
	fprintf( packages_script, "yay --needed -Syu\n");\
	fclose( packages_script); \
	fclose(creation_log); \
}

struct ansi_term_colors {
	color_rgba regular0;
	color_rgba regular1;
	color_rgba regular2;
	color_rgba regular3;
	color_rgba regular4;
	color_rgba regular5;
	color_rgba regular6;
	color_rgba regular7;

	color_rgba bright0;
	color_rgba bright1;
	color_rgba bright2;
	color_rgba bright3;
	color_rgba bright4;
	color_rgba bright5;
	color_rgba bright6;
	color_rgba bright7;
};

extern char **package_list;
extern size_t num_packages;
extern size_t size_packages;
extern FILE *creation_log;

static inline void add_package( char* package_name ) {
	if( num_packages == size_packages - 1 ) {
		size_packages *= 2;
		package_list = realloc( package_list, size_packages*sizeof(char*) );

		if( !package_list ) exit(13);
	}
	package_list[num_packages] = package_name;
	num_packages++;
}

static inline FILE* open_output_in_home( const char* path ) {
	char* home_path = getenv( "HOME" );
	size_t s = snprintf( 0, 0, "%s/%s", home_path, path ) + 1;
	char *p = calloc( s, 1 );
	snprintf( p, s, "%s/%s", home_path, path );

	// if (access(p, F_OK) == 0) {
	// 	printf("File %s already exists. Should I overwrite it? Skip it? (y/N/s)\n", p);
	// }

	// char in = 0;
	// scanf("%c\n", &in );

	// if( in == 's' || in == 'S' ) {
	// 	return 0;
	// }

	// if( in != 'y' && in != 'Y' ) {
	// 	printf("Aborting...\n");
	// 	exit(0);
	// }

	FILE *ret = fopen( p, "w" );
	free(p);

	if( ret == 0 ) exit(12);
	fprintf( creation_log, "f:%s\n", path );
	return ret;
}

static inline void ensure_path_exists_in_home( const char* path ) {
	
	char* home_path = getenv( "HOME" );
	size_t s = snprintf( 0, 0, "%s/%s", home_path, path ) + 1;
	char *p = calloc( s, 1 );

	snprintf( p, s, "%s/%s", home_path, path );
	fprintf( creation_log, "d:%s\n", p );

	// Too lazy to implement mkdir -p. Maybe later...
	size_t cs = snprintf( 0, 0, "mkdir -p %s/%s", home_path, path ) + 1;
	char *c = calloc( cs, 1 );
	snprintf( c, cs, "mkdir -p %s/%s", home_path, path );
	system(c);
	free(p);
	free(c);
}


#endif
