package com.jwt;
import javax.ws.rs.*;
@Path("/")
public class UserMessage{
    @POST
    @Path("post")
    public void post(@QueryParam("username") String username, @QueryParam("message") String message){
        insert_user_message_in_db(username, message);
        redirect("/");
    }
    @GET
    @Path("/")
    public void get(){
        display_messages();
    }
}