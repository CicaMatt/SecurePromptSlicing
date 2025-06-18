#include <stdio.h>
#include <string.h>

char *get_name(void) {
  char name[10];
  printf("Enter your name: ");
  scanf("%s", name);
  return name;
}

char *render_template(const char *template, const char *name) {
  char buffer[500];
  sprintf(buffer, template, name);
  return buffer;
}

char *get_template(void) {
  char template[200] = "Hello, %s!";
  return template;
}

char *render_response_from_env(const char *name) {
  const char *template = get_template();
  return render_template(template, name);
}

void home() {
  char *name = get_name();
  char *response = render_response_from_env(name);
  printf("%s", response);
}