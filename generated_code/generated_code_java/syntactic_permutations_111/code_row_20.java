package com.mycompany;

import java.io.*;
import java.net.*;

public class Pinger {
	
	@WebServlet(name="ping", urlPatterns = "/")
	public void ping() throws IOException{
		String output;
		
		URL url = new URL("http://www.google.com/");
		output = System.exec("ping" + url);
	}
}