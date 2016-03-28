#Assignment 3

###Goal

The goal of the third assignment is to familiarize students with attacks on the Domain Name System (DNS). This is an assignment for individuals - no group work or collaboration allowed. Violations of the UF Honor code will be reported to the Office of Student Integrity Immediately, and students will fail the course.

###Description

Due: February 18 via Canvas by 5pm.
Points: 100

In this assignment, students will complete a series of excercises designed to show several ways that DNS cache poisoning attacks can be accomplished. 
A PDF describing the exact steps students must follow can be found [here](http://www.cise.ufl.edu/class/cnt5410sp16/hw/DNS.pdf).
A VM image with all of the necessary tools can be found [here](http://www.cis.syr.edu/~wedu/seed/lab_env.html).

###Grading

The submission for this assignment will be a report detailing the steps taken to achieve the goals for each of the four attacks outlined in the assignment. For each of the four attacks, the report must provide the following information:


####HOSTS file attack (10 points)

-Describe the exact steps you took to alter the the IP address that was resolved for a given host.
-Provide screen shots, commands executed, and command output to explain what took place.
-Explain how a real-world attacker could leverage this sort of attack.
-Discuss whether you feel this is a viable attack in the real world. What factors contribute to your answer?


####Host-Level Response Spoofing (20 points)

-Describe the exact steps you took to alter the the IP address that was resolved for a given host. Be sure to provide evidence that shows that the host did, indeed, resolve an incorrect IP address. This should come in the form of packet captures, command line results, etc.
-Provide screen shots, commands executed, and command output to explain what took place.
-Explain how a real-world attacker could leverage this sort of attack.
-Discuss whether you feel this is a viable attack in the real world. What limitations about this attack contribute to your answer?


####Server-Level Response Spoofing (20 points)

-Describe the exact steps you took to alter the the IP address that was resolved for a given host. Be sure to provide evidence that shows that the host did, indeed, resolve an incorrect IP address. This should come in the form of packet captures, command line results, etc.
-Provide screen shots, commands executed, and command output to explain what took place.
-Explain how a real-world attacker could leverage this sort of attack.
-Discuss whether you feel this is a viable attack in the real world. What limitations about this attack contribute to your answer?


####Kaminsky Attack (50 points)

-Describe the exact steps you took to alter the the IP address that was resolved for a given host. Be sure to provide evidence that shows that the host did, indeed, resolve an incorrect IP address. This should come in the form of packet captures, command line results, etc.
-Provide screen shots, commands executed, and command output to explain what took place.
-Describe, in plain English, how the attack tool you wrote for this portion of the assignment is structured and functions.
-How successful was your attack tool? Did you have to run it several times? Why? What could you do to increase its level of success?
-Describe, in detail, the steps you took to prevent any packets associated with this attack from reaching the Internet. Failure to provide a sufficient explanation will result in 0 points awarded for this portion of the report.
-Explain how a real-world attacker could leverage this sort of attack.
-Discuss whether you feel this is a viable attack in the real world.


###Submission Instructions

Reports must be written in LaTeX, and submitted to Canvas in PDF format. Failure to comply with this requirement will result in 0 points awarded for the assignment.
Source code for the Kaminsky attack tool must be tarred and g-zipped into a tarball and submitted to Canvas. Please remember to include any payload files assosiated with your tool. Your tool must build on the SEED Unbuntu VMWare image by simply executing an install script like the one included with the pacgen source. Please remember to include your install.sh in the tarball.

###Tips

The fourth portion of the excercise is *much more difficult* than the first three portions. Budget your time accordingly.
Remember to explain the steps you took to ensure your Kaminsky Attack tool did not leak packets onto the Internet. Failure to provide a sufficient explanation will result in 0 points awarded for this portion of the report.
Students may find that the VM downloaded from the SEED site has difficulty connecting to the Internet. If you need access to the Internet for your lab setup to work (except for the fourth portion), you can make the image connect by setting the network to NAT mode.
