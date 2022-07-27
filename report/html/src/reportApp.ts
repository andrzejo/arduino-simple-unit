import {hot} from 'react-hot-loader/root';
import React from "react";
import ReactDOM from "react-dom";
import Report from "./Report/Components/Report";

import "./reportApp.scss"

const handle = document.getElementById("container");
ReactDOM.render(React.createElement(hot(Report)), handle);
