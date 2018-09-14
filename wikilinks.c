#include <stdio.h>

/* Initialize the states:
 * TEXT: Any text outside of a link or template, including whitespace.
 * This text is ignored.
 * LINK_LABEL

*/
#define TEXT 0
#define ONE_START_BRACKET 1
#define LINK 2
#define ONE_START_BRACE 3
#define TEMPLATE 4
#define ONE_END_BRACKET 5
#define ONE_END_BRACE 6
#define LINK_LABEL 7
#define LT_WHITESPACE 8
#define EMBED_WHITESPACE_FIRST 9

int main()
{
  //set the initial state
  state = TEXT;
  //keep track of nested templates
  int nest_temp = 0;
  //loop through all the characters
  int ch = getchar();
  while (ch != EOF)
  {
    switch (state)
    {
      case TEXT:
      if (ch == '{')
      {
        //saw an opening brace, switch to ONE_START_BRACE
        state = ONE_START_BRACE;
      }
      if (ch == '[')
      {
        //saw an opening bracket, switch to ONE_START_BRACKET
        state = ONE_START_BRACKET;
      }

      case ONE_START_BRACKET:
      if (ch == '{')
      {
        //saw a second opening brace, so we know we're in a template
        state = TEMPLATE;
        nest_temp += 1; //iterate the nested template counter
      }
      else {
        state = TEXT;
      }

      case TEMPLATE:
      if (ch == '}')
      {
        //saw a first closing brace, so we move to ONE_END_BRACE
        state = ONE_END_BRACE;
      }

      case ONE_END_BRACE:
      if (ch == '}')
      {
        //saw a second closing brace, so we know we're out of the template
        if (nest_temp == 0)
        {
          state = TEXT;
        }
        else
        {
          state = TEMPLATE;
          nest_temp -= 1;
        }
      }
      else
      {
        state = TEMPLATE;
      }

      case ONE_START_BRACKET:
      if (ch == '[')
      {
        state = LINK;
      }
      else
      {
        state = TEXT;
      }

      case LINK:
      if (ch == '|')
      {
        state = LINK_LABEL;
      }



    }
  }
}
