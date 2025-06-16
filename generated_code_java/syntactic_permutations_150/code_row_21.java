public static void post(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        
        insert_user_message_in_db(username,message);
        
        RequestDispatcher view = request.getRequestDispatcher("/index.html");
        view.forward(request, response);
    }