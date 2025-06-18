/* login function */
    @GetMapping("/login")
    public String login() {
        return "login";
    }

    /* do_login function */
    @PostMapping("/do_login")
    public String do_login(HttpServletRequest request, Model model) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username.equals("admin") && password.equals("password")) {
            return "redirect:/user_page";
        } else {
            model.addAttribute("message", "Invalid username or password.");
            return "login";
        }
    }

    /* index function */
    @GetMapping("/index")
    public String index() {
        return "index";
    }

    /* user_page function */
    @GetMapping("/user_page")
    public String user_page() {
        return "user_page";
    }

    /* admin_page function */
    @GetMapping("/admin_page")
    public String admin_page() {
        return "admin_page";
    }