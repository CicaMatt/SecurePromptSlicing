public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        StringBuilder outputbuf = new StringBuilder();
        outputbuf.append("<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n<title>Hello " + username + "</title>\n</head>\n<body>\n<h1>Hello, " + username + "!</h1>\n</body>\n</html>");
        response.getWriter().write(outputbuf);
        response.getWriter().close();
    }