@RequestMapping(value = "/login", method = RequestMethod.GET)
    public String login() {
        return "login";
    }
    
    @RequestMapping(value = "/do_login", method = RequestMethod.POST)
    public String doLogin(@RequestParam("username") String username,
                          @RequestParam("password") String password) {
        if (isAdmin(username, password)) {
            return "redirect:/admin_page";
        }
        
        // The user is not an admin
        return "login";
    }
    
    private boolean isAdmin(String username, String password) {
        // Check if the user is an admin
        return true;
    }