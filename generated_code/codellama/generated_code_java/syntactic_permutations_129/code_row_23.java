public String render_response_from_env(Environment env){
        Request request = Objects.requireNonNull(RequestContextHolder.getRequestAttributes());
        String name = request.getParameter("name");
        Template template = env.getTemplate("template.html");
        return FreeMarkerTemplateUtils.processTemplateIntoString(template, name);
    }