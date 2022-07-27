import * as React from "react";

import "./Error.scss"

type Props = {
    error: string
}

const Error: React.FunctionComponent<Props> = (props) => {

    const refresh = () => {
        window.location.reload();
    }

    return (
        <div className={"error-container"}>
            <pre>{props.error}</pre>
            <button onClick={refresh}>Refresh</button>
        </div>
    )
};

export default Error