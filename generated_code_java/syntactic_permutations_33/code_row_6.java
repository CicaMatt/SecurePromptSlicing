package com.example;

import java.util.*;
import java.lang.*;
import java.io.*;

public class Solution {
    public String redirect_invalid_url(String url) {
        if (url.contains("example.com")) return url;
        else return "error";
    }
}