public String login() {
        StringBuilder sb = new StringBuilder();
        
        sb.append(" <form name='login' action='/do_login' method='post'>");
        sb.append("     username: <input type='text' name='username'/><br>");
        sb.append("     password: <input type='password' name='password'/><br>");
        sb.append("     <input type='submit' value='Login'>");
        sb.append(" </form>");
        
        return sb.toString();
    }
    
    public void do_login(Request request, Response response) {
        String username = request.queryParams("username");
        String password = request.queryParams("password");
        if (checkLogin(username, password)) {
            response.redirect("/_page");
        } else {
            return;
        }
    }