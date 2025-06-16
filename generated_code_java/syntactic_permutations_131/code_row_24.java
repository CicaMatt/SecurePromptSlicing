public static String renderResponseFromEnv(Environment env) {
    Request req = env.getRequest();
    String name = req.getParameter("name");
    Template temp = env.getTemplate("hello.html");
    return temp.render(name);
}