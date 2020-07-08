#! /bin/sh

insert()
{
	echo "\nEnter ID: -\c"
	read id
	
	echo "Enter name: -\c"
	read name
	
	echo "Enter phone number: -\c"
	read phn
	
	echo "Enter disease: -\c"
	read dis
	
	echo $id"\t"$name"\t  "$phn"\t  "$dis >> hospital.txt

	echo "\nRecord Inserted Successfully!"
}

display()
{
	if [ -s hospital.txt ]
	then
		echo "\nHOSPITAL DATA:"
		echo "\nID\tNAME\tPHONE NUMBER\tDISEASE\n"
		sort hospital.txt
	else
		echo "\nFile is empty!"
	fi
}

search()
{
	if [ -s hospital.txt ]
	then
		echo "\nEnter ID to be searched: -\c"
		read id

		echo "\nID\tNAME\tPHONE Number\tDISEASE\n"
		grep -w $id hospital.txt
	else
		echo "\nFile is empty!"
	fi
}

delete() 
{
	if [ -s hospital.txt ]
	then
		echo "\nEnter ID to be deleted: -\c"
		read id
	
		touch temp.txt

		grep -v -w $id hospital.txt > temp.txt
		mv temp.txt hospital.txt

		echo "\nRecord deleted Successfully!!"
	else
		echo "\nFile is empty!"
	fi
}

modify() 
{
	if [ -s hospital.txt ]
	then
		echo "\nEnter ID to be updated: -\c"
		read id

		echo "\nEnter new phone number:-\c"
		read phn
	
		sed -i "/$id/c\\$id\t$name\t$phn\t$dis" hospital.txt
		#mv temp.txt student.txt

		echo "\nData Modified!!"
		
	else
		echo "\nFile is empty!"
	fi
}

while(true)
	do
	echo "\nHOSPITAL DATABASE:\n1.Create database\n2.Insert Record  \n3.Display Record \n4.Search Record\n5.Delete Record\n6.Modify Record\n7.Exit\nEnter your choice:-\c"
	read choice

	case "$choice" in
			1) if [ -s hospital.txt ]
			   then
			   	rm hospital.txt
			   fi
			   touch hospital.txt
			   echo "\nDatabase created successfully!\n"
			   ;;
			2) insert;;
			3) display;;
			4) search;;
			5) delete;;
			6) modify;;
			7) exit;;
			*) echo "\nYou entered wrong choice"
	esac 
done
