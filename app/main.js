import { route } from "./src/utils/routes.js";

window.onpopstate = () => {
    route(window.location.pathname)
}

route('home')