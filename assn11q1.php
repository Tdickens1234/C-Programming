<!-- Tim Dickens -->
<!-- Assignment 11-->
<!-- Instructor: Jonathan Lehuta -->
<!-- Section: 3 -->
<!-- TA: Ishaan Mohammed -->
<!-- Due: 11/27/17-->
<!-- Semester: Fall 2017-->

<html>
    <head>
        <center><Title> Tim Dickens</title></center>
    </head>
    <head>
	<center> Assignment 11 Question 1, Insert Into horse</center>
        <center><a href="http://students.cs.niu.edu/~z1804759/assn11q2.php">Question 2</a></center>
        <center><a href="http://students.cs.niu.edu/~z1804759/assn11q3.php">Question 3</a></center>
    </head>
    <body>
            <p>
	    Type in a Name, Sire, and Dam to Insert into the Horse Table
            </p>
            <form action ="" method ="post">
            Horse Name <input type ="text" name ="hName"/>
            </p>
            <p>
            Sire Name<input type = "text" name ="sName"/>
            </p>
            <p>
	    Dam Name<input type = "text" name ="dName"/>
            <p>
            <button type = "submit" value ="Submit" name = 'Submit'>Submit</button>
            </p>
            </form>
        <?
//form to collect data to insert into Horse
            include 'usernameinfo.php';
            try{

                   $dsn = "mysql:host=courses;dbname=z1804759;";
                   $pdo = new PDO($dsn, $username, $password);
//creates a pdo to connect with and interact with database
		   if(isset($_POST['Submit']))
                   {
                       $hName = $_POST['hName'];
                       $sName = $_POST['sName'];
                       $dName = $_POST['dName'];
                       $n = $pdo->exec("INSERT INTO horse (name, sire, dam) VALUES ('$hName', '$sName', '$dName');");
                   }
//inserts into database
		   if( $n > 0 )
		   {
                       echo "Updated ". $n. " Rows.";
		   }
//tells how many rows were affected by the query
            }
                catch(PDOexception $exception){ //handles database connection exceptions
                    echo "Connection to Database Failed: ". $exception->getMessage();
                }
        ?>
    </body>
</html>
