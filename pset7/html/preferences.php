<?php

    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["oldPassword"]))
        {
            apologize("You must provide your old password.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide a new password.");
        }
        else if (($_POST["confirmation"] != $_POST["password"]))
        {
            apologize("Your new password must match your confirmation password.");
        }
        
        // get old password hash
        $rows = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        $hash = $rows[0]["hash"];
        
        // compare hash of user's input against hash that's in database
        if (crypt($_POST["oldPassword"], $hash) == $hash)
        {
            // change the users password
            query("UPDATE users set hash = ? WHERE id = ?", crypt($_POST["password"]), $_SESSION["id"]);
            
            // redirect to portfolio
            redirect("/");
        }
        else
        {
            apologize("The old password you entered was incorrect.");
        }
    }
    else
    {
        // else render form
        render("preferences_form.php", ["title" => "Preferences"]);
    }
    
?>
