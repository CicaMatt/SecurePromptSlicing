public String renderResponseFromEnv(Environment environment, Request request) {
        Map parameters = request.getParameters();
        String name = (String) parameters.get("name");
        Template template = environment.getTemplate("hello.ftl");
        Writer out = new StringWriter();
        try {
            template.process(parameters, out);
        } catch (TemplateException e) {
            // logging and handling as appropriate
        }
        return out.toString();
    }