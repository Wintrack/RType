var navlinks = document.getElementById("navlinks");
function showMenu() {
    navlinks.style.display = "flex";
    navlinks.style.right = "0";
}
function hideMenu() {
    navlinks.style.right = "-200px";
    navlinks.style.display = "none";
}