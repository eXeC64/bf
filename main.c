#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MEM_SIZE 30000

unsigned char mem[MEM_SIZE];    /* the working memory/turing tape */
unsigned char* src = NULL;      /* string of brainfuck code being interpreted */
unsigned int src_len = 0;       /* length of brainfuck code being interpreted */
unsigned char* ptr = mem;       /* pointer to current position in memory */
unsigned char* ins = NULL;      /* pointer to current instruction */

void (*instr[256])();           /* function pointer array */
void nop() { ; }                /* no operation */
void inc() { (*ptr)++; }        /* + operation */
void dec() { (*ptr)--; }        /* - operation */
void rht() { ptr++; }           /* > operation */
void lft() { ptr--; }           /* < operation */
void out() { putchar(*ptr); }   /* . operation */
void inp() { *ptr=getchar(); }  /* , operation */
void lbr() {                    /* [ operation */
    if(*ptr!=0) { return; }
    for(int frames = 1; frames > 0; ++ins) {
        if(*(ins+1) == ']') { --frames; }
        if(*(ins+1) == '[') { ++frames; }
    }
}
void rbr() {                    /* ] operation */
    if(*ptr==0) { return; }
    for(int frames = 1; frames > 0; --ins) {
        if(*(ins-1) == ']') { ++frames; }
        if(*(ins-1) == '[') { --frames; }
    }
}

int load_file(char* path, unsigned char** dst, int* len);

int main(int argc, unsigned char** argv) {

    if(argc != 2) {
        printf("Usage: %s <source file>\n", argv[0]);
        exit(1);
    }

    memset(mem, MEM_SIZE, 0);

    for(int i=0;i<256;++i)
        instr[i] = nop;

    instr['+'] = inc;
    instr['-'] = dec;
    instr['>'] = rht;
    instr['<'] = lft;
    instr['.'] = out;
    instr[','] = inp;
    instr['['] = lbr;
    instr[']'] = rbr;

    if(load_file(argv[1], &src, &src_len) != 0) {
        printf("Error reading %s\n", argv[1]);
        return 1;
    }

    for(ins = src; ins < src+src_len; ++ins) {
        (instr[*ins]) ();
    }

    free(src);

    return 0;
}

int load_file(char* path, unsigned char** dst, int* len) {
    FILE* src_file = fopen(path, "r"); 
    if(src_file == NULL) { return 1; }

    fseek(src_file, 0, SEEK_END);
    *len = ftell(src_file);
    fseek(src_file, 0, SEEK_SET);

    *dst = malloc(*len);
    fread(*dst, 1, *len, src_file);
    fclose(src_file);

    return 0;
}
