@GetMapping("/login")
    public String login() {
        return "form";
    }

@PostMapping("/dologin")
    public String doLogin(@RequestParam("username") String username, @RequestParam("password") String password) {
        if(isAdmin()) {
            redirect("/admin_page");
        } else {
            return "error";
        }
    }