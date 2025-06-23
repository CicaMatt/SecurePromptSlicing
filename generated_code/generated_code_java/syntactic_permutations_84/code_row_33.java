package com.mashup.api

    import java.io.IOException;
    import javax.servlet.ServletException;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;

    public class MashupApi {
        private String payload = null;

        public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            if (request.getParameter("payload") != null) {
                payload = request.getParameter("payload");
                try {
                    if (payload.contains("Create")) {
                        response.sendError(HttpServletResponse.SC_NOT_FOUND);
                    }
                } catch (Exception e) {
                    System.out.println("An exception occurred: " + e.getMessage());
                }
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST);
            }
        }
    }