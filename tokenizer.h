char** tokenize(char* str, const char delim);
bool delim_character(char c, char delim);
bool non_delim_character(char c, char delim);
char *word_start(char* str,char delim);
char *end_word(char* str,char delim);
int count_tokens(char* str,char delim);
char *copy_str(char *inStr, long len, char delim);
void print_all_tokens(char** tokens);

char** tokenize(char* str, char delim)
{
   int n = count_tokens(str, delim);
   char** token = (char**)malloc((n+1)*sizeof(char*));
   char* start;
   char* end;
   int i = 0;

   for (i = 0; i < n; i++){
   
      start = word_start(str,delim);
      end = end_word(start, delim);
      token[i] = copy_str(start, end - start, delim);
      printf("Length: %d\n", (end-start));
      str = end;
   }

   token[i] = NULL;

   return token;

}
/* Return true (non-zero) if c is the delimiter character
   previously chosen by the user.
   Zero terminators are not printable (therefore false) */
bool delim_character(char c, char delim)
{
      if(c == delim){
         return true;
      }else{
         return false;
      }
}
/* Return true (non-zero) if c is a non-delimiter
       character Zero terminators are not printable (therefore false) */
bool non_delim_character(char c, char delim)
{
   if(c != delim){
      return true;
   }else{
      return false;
   }
}

/* Returns a pointer to the first character of the next
   word starting with a non-delimiter character. Return a zero pointer if
   str does not contain any words.*/
char *word_start(char* str,char delim)
{
   int i = 0;
   
   while(i < strlen(str)){
      if(non_delim_character(str[i], delim)){
         return str = &(str[i]);
         break;
      }
      i++;
   }
   
}

/* Returns a pointer to the first delimiter character of the zero
   terminated string*/
char *end_word(char* str,char delim)
{
   str = word_start(str, delim);
   int i = 0;
   
   while(i < strlen(str)){
      if(delim_character(str[i], delim)){
         return str = &(str[i]);
         break;
      }
      i++;
   }

}

/* Counts the number of words or tokens*/
int count_tokens(char* str,char delim)
{
   int tokenNum = 0;
   int i =0;

   while(str[i] != '\0'){

      str = word_start(str, delim);
      str = end_word(str, delim);
      tokenNum++;
      i++;
   }

   return tokenNum;

}

/* Returns a freshly allocated new zero-terminated string
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, long len, char delim)
{
   char *strCp = (char*)malloc( (len+1)*sizeof(char) );
   char *temp = strCp;
   
   for(int i = 0; i < len; i++){
      *strCp = *inStr;
      strCp++;
      inStr++;
   }
   *strCp = '\0';
   return temp;
}

void print_all_tokens(char** tokens)
{  
   int count = 0;
   while(*tokens != NULL){
      printf("Tokens [%d]: %s\n", count, *tokens);
      tokens++;
      count++;
   }
   printf("\n");
}