# blood_bank
A simple C++ based blood bank management system. This system allows *admin, **donors, and **patients* to interact with the blood bank. The admin can manage blood stock, while donors can donate blood, and patients can request blood for their needs. The system keeps track of the available stock and ensures that the requested blood group is available when needed.

## Features

•⁠  ⁠*Admin Panel*: 
    - View and manage blood stock.
    - Access restricted by an admin password.
    
•⁠  ⁠*Donor Panel*:
    - Donors can donate blood and specify the blood group and quantity.
    - Updates the available stock when a donation is made.
    
•⁠  ⁠*Patient Panel*:
    - Patients can request blood of a specific group.
    - Reduces the available stock when a blood packet is allocated to a patient.

## Installation

1.⁠ ⁠Make sure you have a C++ compiler installed (e.g., GCC or Clang).
2.⁠ ⁠Clone the repository to your local machine:
   git clone https://github.com/Zeni1210/blood_bank.git
