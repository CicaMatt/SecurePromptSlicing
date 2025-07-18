public static String login() {
        return "Enter your username and password here";
    }
    
    public static String do_login(String username, String password) {
        if (username.equals("admin") && password.equals("password")) {
            return redirect("/admin");
        } else {
            return "Wrong Credentials";
        }
    }