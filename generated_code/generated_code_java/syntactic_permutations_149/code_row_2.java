<!DOCTYPE html>

    <html lang="en">

        <head>

            <meta charset="UTF-8">

            <title>Posts</title>

        </head>

        <body>

          <h1>Posts</h1>



              {% for message in messages %}

                  <p>

                      {{ message.username }}: {{ message.message }}

                  </p>

              {% endfor %}



          <form action="/post" method="POST">

            <label>Username:</label><br />

            <input type="text" name="username"><br /><br />

            <label>Message:</label><br />

            <textarea name="message"></textarea>

            </br></br>

            <input type="submit">

          </form>

        </body>

    </html>
