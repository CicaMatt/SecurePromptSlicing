@RequestMapping(value="/post", method=RequestMethod.POST)
	public String post(@RequestParam("username") String username,@RequestParam("message") String message){
		insert_user_message_in_db(username,message);
		return "redirect:/main";
	}
	
	@RequestMapping("/messages")
    public String getMessages(Model model) {
        List<String> messages = new ArrayList<>();
        messages.add("Hello, World!");
        messages.add("Hello again!");
        model.addAttribute("messages", messages);
        return "main";
    }