package com.journaldev.spring;

import java.util.ArrayList;
import java.util.List;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.servlet.ModelAndView;

@RestController
public class HomeController {
	
	private UserService userService;
	
	@Autowired
	public void setUserService(UserService userService) {
		this.userService = userService;
	}

	@RequestMapping("/")
	public ModelAndView home() {
		ModelAndView modelAndView = new ModelAndView("home");
		List<String> messages = getMessages();
		modelAndView.addObject("messages", messages);
		return modelAndView;
	}

	@RequestMapping(value="/post", method=RequestMethod.POST)
	public String postMessage(String username, String message) {
		userService.insertMessage(username,message);
		return "redirect:/";
	}
	
	private List<String> getMessages() {
		List<String> messages = new ArrayList<String>();
		messages.add("Welcome to JournalDev");
		messages.add("We are here to help you learn");
		return messages;
	}
	
}