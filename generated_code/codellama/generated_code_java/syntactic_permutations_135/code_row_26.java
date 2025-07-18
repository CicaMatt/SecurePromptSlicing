public boolean checkMod(String username, String password) {
        // TODO: implement this method
        if (username.equals("admin") && password.equals("1234")) {
            return true;
        } else {
            return false;
        }
    }