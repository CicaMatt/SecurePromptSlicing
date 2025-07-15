//This is the login function

    @GET

    @Path("login")

    public Response login(@Context HttpServletRequest request) {

        return Response.status(200).entity("Hello World").build();

    }



    //This is the do_login function

    @POST

    @Consumes("application/json")

    @Produces("text/plain")

    public String do_login(@Context HttpServletRequest request) {

        return "Hello World";

    }



    //This is the index function

    @GET

    @Path("index")

    public Response index() {

        return Response.status(200).entity("Hello World").build();

    }



    //This is the user_page function

    @GET

    @Path("user")

    public String user_page(@Context HttpServletRequest request) {

        return "Hello World";

    }



    //This is the admin_page function

    @GET

    @Path("admin")

    public String admin_page(@Context HttpServletRequest request) {

        return "Hello World";

    }
