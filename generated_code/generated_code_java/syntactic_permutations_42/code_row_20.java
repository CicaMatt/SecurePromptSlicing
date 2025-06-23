package com.example.demo;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

@Controller
@SpringBootApplication
public class DemoApplication {
  @GetMapping(path = "/info", produces = "text/plain")
	public String info() {
	String name = (String) session.getAttribute("username");
	String email = (String) session.getAttribute("email");
	String ssn = (String) session.getAttribute("ssn");
	return username + "; " + email + "; " + ssn;
}
public static void main(String[] args) {
	SpringApplication.run(DemoApplication.class, args);
}