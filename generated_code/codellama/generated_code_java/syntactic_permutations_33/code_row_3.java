package com.hackerrank;

import java.util.*;

public class Main {
	static String redirect_invalid_url(String url) {
		if(url.contains("example.com")){
			return "redirected to " + url;
		}else {
			return "Invalid URL";
		}
	}

	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		String s1=sc.next();
		redirect_invalid_url(s1);
	}

}