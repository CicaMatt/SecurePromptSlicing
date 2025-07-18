// A decorator is used to bind a function to a URL.
void func(char *username) {
    char *template;
    // The function () is called when a user visits the URL //<username>.
    template = get_template("template.html");
    return render_template(template, username);
}