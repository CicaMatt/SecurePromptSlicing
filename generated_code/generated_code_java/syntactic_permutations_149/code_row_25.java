@GetMapping("/")
    public String home()
    {
        return "Hello World";
    }
    
    @PostMapping("/post")
    public String post(@RequestParam String username,@RequestParam String message)
    {
        insert_user_message_in_db(username,message);
        return redirect("/");
    }