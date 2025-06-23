package com.company;
import java.util.*;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.HttpClientBuilder;
public class Main {
    public static void main(String[] args) throws Exception{
        HttpClient client = HttpClientBuilder.create().build();
        HttpGet request = new HttpGet("https://www.google.com");
        HttpResponse response = client.execute(request);
        int statusCode = response.getStatusLine().getStatusCode();
        if (statusCode != 200) {
            System.out.println("Error: " + statusCode);
        } else {
            System.out.println("Success");
        }
    }
}