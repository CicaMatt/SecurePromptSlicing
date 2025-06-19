package com.app;
import java.util.*;
public class Main {
	static boolean auth_mod(String name, String password, String session) {
        // ...
    }
	static void check_mod() {
	    String name = request.getParameter("name");
	    String password = request.getParameter("password");
	    String session = request.getParameter("session");
        if(auth_mod(name, password, session)) {
            // ...
        } else {
            // ...
        }
	}
}