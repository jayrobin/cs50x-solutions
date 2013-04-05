<?php

    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        else if (($_POST["confirmation"] != $_POST["password"]))
        {
            apologize("Your password must match your confirmation password.");
        }
        
        $username = $_POST["username"];
        
        // ensure user doesn't already exist
        $rows = query("SELECT * FROM users WHERE username = ?", $username);
        if(count($rows) == 0)
        {
            // insert user into database
            query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $username, crypt($_POST["password"]));
            
            // get id of new user
            $rows = query("SELECT * FROM users WHERE username = ?", $username);

            // check to ensure user was added
            if (count($rows) == 1)
            {
                $id = $rows[0]["id"];
                
                $_SESSION["id"] = $id;

                // redirect to portfolio
                redirect("/");
            }
            else
            {
                apologize("There was a problem registering your account.");
            }
         }
         else
         {
            apologize("That username already exists, please choose another.");
         }
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }
    
?>
