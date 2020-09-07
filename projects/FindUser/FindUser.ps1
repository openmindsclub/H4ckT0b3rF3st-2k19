Import-Module ActiveDirectory

$computer = Read-Host "What is the name of the computer: "
$dns = Resolve-DnsName -Name $computer
$ip = $dns.IPAddress


#Test the connection to the computer. If it is offline it provides the last known IP address. 
ElseIF(!(Test-Connection -ComputerName $dns.address -BufferSize 16 -ErrorAction 0 -Count 1 -Quiet)){ 
    Write-Host "The computer offline. Last known IP address: $IP"
}

#Checks to see if No One is logged in. 
else{
    $username = Get-WmiObject win32_computersystem -computername $computer -Property username | Select-Object -ExpandProperty username 
    if($username -eq $null)
    }
    {
    Write-Host "No one is currently logged into $computer" 
    }

#Provides the user that is currently logged into the computer. 
else{
    Write-Host "`n"
    $ADuser = $username.Replace("DOMAIN\","") 
    $ADusers = Get-ADUser -Identity $ADuser -Properties name | Select-Object name
    $Name = $ADusers.name
    Write-Host "Username: $ADuser" 
    Write-Host "Name: $Name" }
;