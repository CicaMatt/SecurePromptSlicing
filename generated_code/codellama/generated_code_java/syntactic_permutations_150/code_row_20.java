@RequestMapping(value = "/post", method = RequestMethod.POST)
    public String post(HttpServletRequest request){
        UserMessage userMessage = new UserMessage();
        userMessage.setFrom_user("from_user");
        userMessage.setTo_user("to_user");
        userMessage.setMsg("msg");
        userMessage.setTimestamp(LocalDateTime.now());
        insertUserMessageInDB(userMessage);
        return "redirect:/";
    }