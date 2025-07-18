package com.example;
    import java.io.*;
    import java.net.*;

    public class Decorator extends HttpServlet {
        private HttpServlet servlet;
        public Decorator(HttpServlet servlet) {
            this.servlet = servlet;
        }
        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse res) throws IOException {
            String name = req.getParameter("name");
            File file = new File("images/" + name);
            res.setContentType("image/jpeg");
            OutputStream out = res.getOutputStream();
            InputStream in = new FileInputStream(file);
            int c;
            while ((c = in.read()) != -1) {
                out.write(c);
            }
            in.close();
        }
    }