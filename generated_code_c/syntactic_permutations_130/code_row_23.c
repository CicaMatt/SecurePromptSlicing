char *render_response_from_env(const char *env) {
    const char *name = get_param_from_request("name");
    const char *template = get_template_from_env(env);
    return render_template(template, name);
}