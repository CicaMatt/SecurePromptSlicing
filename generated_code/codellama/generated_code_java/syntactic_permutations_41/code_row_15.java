package com.github.nayan723;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class NayanWebApp {
	public static void main(String[] args) {
    Spark.get("/", (req, res) -> {
      return "Welcome to the world of Java!";
    });
  }
}